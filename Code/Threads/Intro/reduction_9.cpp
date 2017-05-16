#include <thread>
#include <vector>
#include <iostream>
#include <numeric>

template <typename ITERATOR, typename T>
struct sum_operator
{
	void operator()(ITERATOR i_first, ITERATOR i_last, T& io_result){

		io_result=std::accumulate(i_first,i_last,T());

	}
};


template <typename ITERATOR, typename T>
T parallel_sum(ITERATOR i_first, ITERATOR i_last, const unsigned int i_num_threads, const T i_init){
	
    // Compute data size
	const unsigned long int data_size = std::distance(i_first,i_last);
	if(data_size == 0)
		return i_init;
	
	// Check number of hardware limits to avoid oversubscription
	const unsigned long int num_threads = std::min(i_num_threads, std::thread::hardware_concurrency());
	
	// Compute data size for each thread
	const unsigned long int data_block_size = data_size/num_threads;
	
	// Create thread pool
	std::vector<T> results(num_threads);
	std::vector<std::thread> threads(num_threads-1);
	ITERATOR block_first(i_first);
	for(unsigned long int i=0;i<(num_threads-1);++i)
	{
		ITERATOR block_last(block_first+data_block_size);
		threads[i] = std::thread{sum_operator<ITERATOR,T>(),block_first,block_last,std::ref(results[i])};
		block_first = block_last;
	}
	sum_operator<ITERATOR,T>()(block_first,i_last,std::ref(results[num_threads-1]));
	
	// Wait for threads to complete their work
	for(unsigned long int i=0;i<num_threads-1;++i)
	{
		threads[i].join();
	}
	
	// Sum partial results
	return std::accumulate(results.begin(),results.end(),i_init);
}


int main()
{
	// Create data set
	std::vector<int> data(100,1);

	// Compute sum
	double sum = parallel_sum(data.begin(),data.end(),4,0);

	// Print result
	std::cout<<"Sum value is: "<<sum<<std::endl;
}
