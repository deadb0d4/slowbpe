# slowbpe

## Intro

Karpathy's [Let's build the GPT Tokenizer](https://youtu.be/zduSFxRajkE?si=ES9gE_VCrkfKiYVd) introduces the [BPE algorithm](https://en.wikipedia.org/wiki/Byte_pair_encoding) among other things. I was curious to learn more efficient implementation of the algorithm, and had hard time either finding resources on the topic or coming up with something myself. I managed to find great references on the topic, but not tutorials, so figured to make one myself.

## Goals

- [x] Implement an algorithm from https://en.wikipedia.org/wiki/Byte_pair_encoding naively
- [x] Check-in benchmarks (for possible future work, one text file for now)
- [x] Implement a faster implementation with lots of comments

## References

- https://github.com/karpathy/minbpe
- https://arxiv.org/pdf/2306.16837
- https://guillaume-be.github.io/2021-09-16/byte_pair_encoding
- https://github.com/vkcom/youtokentome
- https://github.com/JohannesVod/QuickBPE

## Benchmarks

I implemented very simple v1 that is still pretty slow as compared to some of the references above, but is faster than the naive implementation. Here is the command I used after running `./run/build.sh bench`:
```
$ ./build/benchmark_tinyshakespeare --benchmark_repetitions=10 --benchmark_report_aggregates_only=true | grep -e "_mean" -e "_stddev"
Unable to determine clock rate from sysctl: hw.cpufrequency: No such file or directory
2024-11-09T20:13:15+00:00
Running ./build/benchmark_tinyshakespeare
Run on (8 X 24.0784 MHz CPU s)
CPU Caches:
  L1 Data 64 KiB (x8)
  L1 Instruction 128 KiB (x8)
  L2 Unified 4096 KiB (x4)
Load Average: 3.34, 2.98, 2.96
BM_Slow/1024/100_mean        3722860 ns      3718322 ns           10
BM_Slow/1024/100_stddev        14024 ns        11121 ns           10
BM_Slow/4096/100_mean       14566275 ns     14550490 ns           10
BM_Slow/4096/100_stddev        58052 ns        52598 ns           10
BM_Slow/1024/1000_mean      10063211 ns      9925872 ns           10
BM_Slow/1024/1000_stddev      573923 ns       293269 ns           10
BM_Slow/4096/1000_mean     100624000 ns    100471643 ns           10
BM_Slow/4096/1000_stddev      824623 ns       745526 ns           10
BM_v1/1024/100_mean           245170 ns       245078 ns           10
BM_v1/1024/100_stddev           5452 ns         5411 ns           10
BM_v1/4096/100_mean           878433 ns       866119 ns           10
BM_v1/4096/100_stddev          49806 ns        12268 ns           10
BM_v1/1024/1000_mean          677008 ns       676717 ns           10
BM_v1/1024/1000_stddev          4577 ns         4539 ns           10
BM_v1/4096/1000_mean         2004280 ns      2003627 ns           10
BM_v1/4096/1000_stddev          9422 ns         9264 ns           10
BM_v1/1048576/100_mean     163088017 ns    160893200 ns           10
BM_v1/1048576/100_stddev    11284323 ns      4872622 ns           10
BM_v1/1048576/1000_mean    259297729 ns    259222200 ns           10
BM_v1/1048576/1000_stddev    2981667 ns      2943916 ns           10
BM_v1/1048576/5000_mean    380204143 ns    380061600 ns           10
BM_v1/1048576/5000_stddev    5809626 ns      5752088 ns           10
```

As a result, I will stop working on this for now. I am pretty curious how do people solve fit BPE at scale using e.g. mapreduce.
