extern "C" {
#include "data-structures/arrays/c/cvector.h"
}

#include <benchmark/benchmark.h>

static void BM_CVector_Push(benchmark::State& state) {
  // Perform setup here
  auto obj = cvector_new();

  for (auto _ : state) {
    // This code gets timed
    cvector_push_int(obj, 0);
  }
  state.SetComplexityN(state.range(0));
}

// Register the function as a benchmark
BENCHMARK(BM_CVector_Push)->Range(1, 1 << 20)->Complexity();

static void BM_CVector_Insert(benchmark::State& state) {
  // Perform setup here
  auto obj = cvector_new();
  cvector_resize_ints(obj, state.range(0));

  for (auto _ : state) {
    state.PauseTiming();
    auto index = int{rand() % cvector_size_ints(obj)};
    state.ResumeTiming();
    // This code gets timed
    cvector_insert_int(obj, index, 0);
  }
  state.SetComplexityN(state.range(0));
}

// Register the function as a benchmark
BENCHMARK(BM_CVector_Insert)->Range(1, 1 << 20)->Complexity();

// Run the benchmark
BENCHMARK_MAIN();