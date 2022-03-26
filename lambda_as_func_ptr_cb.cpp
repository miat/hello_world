#include <stdio.h> 
#include <stdlib.h>

// Function without context pointer
typedef void (*callback_t) (int n);

typedef void (*callback_closure_t) (int n, void* context);

/** Function with C-callback argument without context pointer. */
void dotimes_version1(int size, callback_t fun)
{
    printf(" [TRACE] <ENTRY> Called function: %s \n", __FUNCTION__);
    for(int i = 0; i < size; i++){ fun(i); }
    printf(" [TRACE] <EXIT> Called function: %s \n", __FUNCTION__);
}

/** Function with C-callback argument with context pointer for passing function state to
 *  to the function pointer. 
 */
void dotimes_version2(int size, callback_closure_t fun, void* context)
{
    printf(" [TRACE] <ENTRY> Called function: %s \n", __FUNCTION__);
    for(int i = 0; i < size; i++){ fun(i, context); }
    printf(" [TRACE] <EXIT> Called function: %s \n", __FUNCTION__);
}

#include <iostream>
#include <functional> // std::function container 
#include <cassert>

using FunctionCallback1 = std::function<void (int )>;

/** Namespace contains workarounds for passing capturing lambdas 
 * to function dotimes_version (C function without context void pointer)
 * 
 * Note: This solution is not thread-safe. The most suitable workaround for
 * for passing capturing lambdas or C++ functors to C-callbakcs is to 
 * redesign it for using a context void pointer, that allows passing state 
 * to the C-callback.
 *----------------------------------------------------------------------*/
namespace Workaround1 {

	/* This function encapsulates callback global variable 
	** for avoiding the global-initialization fiasco. 
	*-----------------------------------------------------*/
	auto get_callback() -> FunctionCallback1&
	{
		// Global variable, its lifetimes corresponds to the program lifetime.
		static FunctionCallback1 callback;
		return callback;
	};

	/** Set global variable callback */
	auto set_callback(FunctionCallback1 func) -> void 
	{
		auto& callback = get_callback();
		callback = func;
	}

	void workaround1_callback_adapter(int n)
	{
		get_callback()(n);
	}

	/* Disadvantage: This solution is not thread-safe and requires locks 
	*  to protect the callback global state. Only one callback can be 
	*  passed per thread.  
	*/
	void wrapper_to_dotimes_version1(int size, FunctionCallback1 func)
	{
		set_callback(func);
		dotimes_version1(size, &workaround1_callback_adapter);
	}

}

struct FunctionObject 
{	
	int counter = 10;

	FunctionObject(){ }
	FunctionObject(int cnt): counter(cnt){}

	void operator()(int n)
	{
		std::printf("  [FUNCTOR ] n = %d  / counter = %d \n", n, counter++);
	}
};

void FunctionObject_adapter(int n, void* context)
{
	assert(context != nullptr);
	// Note: C-style cast also works, but prefer C++-style cast.
	FunctionObject* pFunctor = static_cast<FunctionObject*>(context);
	
	// [Also works in this way =>>] pFunctor->operator()(n);
	(*pFunctor)(n);
}


int main(int argc, char** argv)
{
	std::puts(" [INFO] Consumer started OK.");

	/* EXPERIMENT 1 - Passing non-capturing lambda to C-function pointer callbacks without 
	* void context pointer. 
	*/
	std::puts("\n ===== [EXPERIMENT 1] Passing non-capturing lambdas ===============\n");
	{		
		/** Non-capturing lambdas are converted to function pointers. */
		dotimes_version1(5, [](int n){
			std::printf(" [EXPERIMENT 1] n = %d \n", n);
		});

	}

	/* EXPERIMENT 2 - Passing capturing lambda to C-function pointer callbacks without
	 * void context pointer. 
	 *
	 * This experiment fails as capturing lambdas cannot be converted to function-pointers. 
	 */
	std::puts("\n ===== [EXPERIMENT 2] Passing Capturing lambdas <FAILURE>  ========= \n");
	{
		int counter = 10;
		auto lamb = [&counter](int n){ 
			std::printf("  [EXPERIMENT 2] n = %d  / counter = %d \n", n, counter++);
		};

		/*  COMPILE-TIME-ERROR: Non-capturing lambdas cannot be passed to 
		 *  to function-pointers !!!
		 *  Remove the next comment ('//') in order to see the compile-time error:
		 * 
		 * Error: 
		 * ---------------------------------------------------------------
		 *  
		 *  [build] cpp-lambda-c/consumer.cpp:30:3: error: no matching function for call to 'dotimes_version1'
         *  [build]                 dotimes_version1(5, lamb);
         *  [build]                 ^~~~~~~~~~~~~~~~
         *  [build] consumer.cpp:7:17: note: candidate function not viable: no known conversion from '(lambda at /home/mxpkf8/temp-projects/cpp-lambda-c/consumer.cpp:26:15)' to 'callback_t' (aka 'void (*)(int)') for 2nd argument
         *  [build] extern "C" void dotimes_version1(int size, callback_t fun);
         *  [build]                 ^
		 ****************************************************************/
		
		// Change from '0' to '1' to enable the compile-time error.
		#if 0  
		  // => Compile-time error! 
		  dotimes_version1(5, lamb); 
		#endif 

	}

	/* EXPERIMENT 3 - Passing capturing lambda to C-function pointer callbacks without
	 * void context pointer using a global-state workaround.
	 */
	std::puts("\n ===== [EXPERIMENT 3] Passing Capturing lambdas - Workaround 1  =====\n");	
	{
		int counter = 10;
		auto lamb = [&counter](int n){ 
			std::printf("  [EXPERIMENT 3] n = %d  / counter = %d \n", n, counter++);
		};

		std::puts("\n --->> Passing C++ capturing lambda ");
		Workaround1::wrapper_to_dotimes_version1(5, lamb);

		std::puts("\n --->> Passing function-object (aka C++ Functor) ");
		Workaround1::wrapper_to_dotimes_version1(5, FunctionObject(25));
	}

	/* EXPERIMENT 4 - Passing capturing lambda to C-function pointer callbacks with
	 * void context pointer. 
	 */
	std::puts("\n ===== [EXPERIMENT 4] Passing Functors to capturing lambda ==\n");	
	{
		std::puts("\n  --->> Passing function-object (aka C++ Functor) [APPROACH 1] ");
		FunctionObject obj1(26);
		dotimes_version2(5, &FunctionObject_adapter, &obj1);

		// Note: This lambda can only be passed due to it be non-capturing.
		auto adapter_for_FunctionObject = [](int n, void* context)
		{
			assert(context != nullptr && "Context pointer should not be nullptr.");			
			FunctionObject* pFunctor = reinterpret_cast<FunctionObject*>(context);
			pFunctor->operator()(n);
		};

		std::puts("\n   --->> Passing function-object (aka C++ Functor) [APPROACH 2] ");
		FunctionObject obj2;
		dotimes_version2(5, adapter_for_FunctionObject, &obj2);
	}

	/* EXPERIMENT 5 - Passing capturing lambda to C-function pointer callbacks with
	 * void context pointer. 
	 */
	std::puts("\n ===== [EXPERIMENT 5] Passing Capturing lambdas <APPROACH 1> ==\n");	
	{		
				
		using FunctionCallback2 = std::function<void (int size)>;
	
		auto adpter_for_lambda = [](int n, void* context) 
		{
			assert(context != nullptr && "Context pointer (state) should not be null.");
			FunctionCallback2* pFunc = reinterpret_cast<FunctionCallback2*>(context);
			(*pFunc)(n);
		};				

		int counter = -100;
		auto callback_lambda = [&counter](int n){ 
			std::printf("  [EXPERIMENT 5] n = %d  / counter = %d \n", n, counter++);
		};
		FunctionCallback2 callback_object = callback_lambda; 

		std::puts("\n  --->> Passing capturing lambda [APPROACH 1 - Type erasure] --- ");
		dotimes_version2(5, adpter_for_lambda, &callback_object);

	}

	std::puts("\n\n [INFO] System shutdown gracefully Ok.");
	return 0;
}
