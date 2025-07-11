1 Introduction
Sorting is a fundamental operation in computer science, and efficient sorting algorithms
are crucial for the performance of many applications. Bucket-Sort is a
comparison-based sorting algorithm that distributes elements into a number of
buckets, each of which is then sorted individually. This report focuses on the implementation
and analysis of both sequential and parallel versions of Bucket-Sort.
The parallel version utilizes OpenMP for parallelization to leverage multi-core
processors, aiming to reduce sorting time significantly.
2 Problem Description
The task involves implementing both sequential and parallel versions of the Bucket-
Sort algorithm in C. The goal is to evaluate the performance of both implementations
under various conditions, including different input sizes and numbers of
buckets. The performance metrics include running time and scalability. The implementation
should ensure correctness, efficiency, and effective use of system resources.
3 Solution Method
3.1 Sequential Bucket-Sort
The sequential version of Bucket-Sort involves the following steps:
1. Variables Definition and Input: Initialize variables and allocate memory
for arrays.
2. Counting Elements for Each Bucket: Distribute elements into appropriate
buckets.
3. Storing Elements in Buckets: Place elements into buckets based on their
values.
4. Sorting Buckets: Sort each bucket using the quicksort algorithm.

3.2 Parallel Bucket-Sort
The parallel version of Bucket-Sort, implemented using OpenMP, involves the
following steps:
1. Variables Definition and Input: Initialize variables and arrays, similar
to the sequential version, including memory allocation for buckets and the
input/output arrays.
2. Element Distribution into Buckets: Elements from the input array are
assigned to buckets based on their value range. This step is performed serially.
3. Sorting Buckets in Parallel: Using #pragma omp parallel for schedule(dynamic),
each thread is assigned one or more buckets to sort independently using the
qsort function. Dynamic scheduling helps balance the load among threads
when bucket sizes vary.
4. Validation: After sorting, the full output array is validated to ensure the
sorting is correct.

4 Experiments
This section presents the experiments conducted to validate and evaluate the performance
of the sequential and parallel versions of the Bucket Sort algorithm.

4.1 Correctness of Code
To ensure the correctness of the implemented sorting algorithms, a verification test
was used in the code. After sorting, the output array is sequentially checked to confirm that each element is less than or equal to its successor. This verification
step is executed automatically for both sequential and parallel versions and prints
confirmation messages to notify whether the data is correctly sorted. All tested
configurations confirmed correct sorting.

4.2 Performance Evaluation
Performance was evaluated based on execution time across various input configurations.
Tests were run with an array size of 2,000,000 elements and bucket counts of
10, 40, 100, and 400. Each configuration was tested under three distribution types:
Uniform, Normal, and Exponential. The results below summarize the sorting time
in seconds for each variant.
4.3 Observation and Results
The performance evaluation of the Bucket-Sort algorithm in both sequential and
parallel implementations yielded several key observations and insights. Below, we
discuss these observations in detail, based on the execution times recorded for
varying bucket counts.
4.3.1 Sequential Implementation
In the sequential version, we observed that the execution time increased as the
number of elements grew, which is expected. We tested the code using three different
distributions: uniform, normal, and exponential. Each distribution affected
how the data was spread across the buckets. The performance differences between
the distributions were not always the same. In some cases, normal distribution
performed faster than expected, while in others, it was slightly slower. This seems
to depend on how balanced the data is across the buckets. For instance, if too many values fall into a few buckets, those take longer to sort. But if the data is
more evenly spread, the sorting becomes faster overall. We also tested different
bucket counts. Increasing the number of buckets generally helped reduce sorting
time, but after a certain point the overhead of managing many buckets started to
cancel out the benefit.

4.3.2 Parallel Implementation
The parallel implementation used OpenMP to parallelize the sorting phase by
assigning each bucket’s sort operation to a separate thread. To improve load
balancing, we compared performance with and without schedule(dynamic). Using
dynamic scheduling significantly improved execution time, especially for uneven
distributions like normal and exponential, where load imbalance is more wellknown.
Without dynamic scheduling, threads assigned to less populated buckets
would finish early and remain idle while others sorted larger buckets. This resulted
in poor CPU utilization. Dynamic scheduling allowed idle threads to take on
additional work, improving overall balance and reducing execution time. Tests
showed that parallel execution produced significant performance gains over the
sequential version when the dataset size was large enough. For smaller arrays, the
time spent managing threads sometimes canceled out the speed advantage of using
parallelism. This shows how important it is to pick the right way to use parallel
processing based on how big the data is.

4.3.3 Speedup Analysis
The speedup achieved by the parallel implementation is a crucial metric for evaluating
its performance. Speedup is defined as the ratio of the execution time of
the sequential algorithm to the execution time of the parallel algorithm.

5 Conclusions
The performance analysis of both the sequential and parallel implementations of
the Bucket-Sort algorithm reveals several key insights. The sequential version
of the algorithm exhibits linear time complexity when the number of buckets is
appropriately chosen, providing efficient sorting for large datasets. However, the
execution time increases significantly with larger input sizes, which highlights the
need for parallelization to improve performance.
The parallel implementation using OpenMP demonstrates significant speedup compared
to the sequential version. This speedup becomes more pronounced with
larger datasets and an increased number of buckets. The results show that the
parallel algorithm scales well with the number of threads up to a certain point, beyond
which the speedup gain diminishes due to overheads such as synchronization
and memory access contention.
The parallel implementation achieves the best performance improvement for larger
arrays and a higher number of buckets.
The scalability of the parallel algorithm is limited by the number of physical cores
available in the system. Beyond a certain number of threads, the overhead outweighs
the benefits of parallelization.
The choice of the number of buckets is critical for optimizing performance in both
sequential and parallel versions. An optimal number of buckets leads to a balanced
workload distribution and minimizes sorting time.
Future work can focus on further optimizing the parallel implementation by reducing
synchronization overhead and improving memory access patterns. Additionally,
exploring hybrid parallelism using both OpenMP and MPI could yield even
better performance for distributed memory systems.
In conclusion, the parallel Bucket-Sort algorithm is an effective solution for sorting
large datasets, leveraging the power of multi-core processors to achieve significant
reductions in execution time. The study underscores the importance of parallel
computing in modern data processing tasks and provides a foundation for further
research and optimization in this area.
