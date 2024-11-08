# slowbpe

## Intro

Karpathy's [Let's build the GPT Tokenizer](https://youtu.be/zduSFxRajkE?si=ES9gE_VCrkfKiYVd) introduces the [BPE algorithm](https://en.wikipedia.org/wiki/Byte_pair_encoding) among other things. I was curious to learn more efficient implementation of the algorithm, and had hard time either finding resources on the topic or coming up with something myself. I managed to find great references on the topic, but not tutorials, so figured to make one myself.

## Goals

- [x] Implement an algorithm from https://en.wikipedia.org/wiki/Byte_pair_encoding naively
- [ ] Check-in benchmarks
- [ ] Implement a faster implementation with lots of comments

## References

- https://github.com/karpathy/minbpe
- https://arxiv.org/pdf/2306.16837
- https://guillaume-be.github.io/2021-09-16/byte_pair_encoding
- https://github.com/vkcom/youtokentome
- https://github.com/JohannesVod/QuickBPE
