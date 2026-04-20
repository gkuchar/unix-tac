#!/usr/bin/env bash
set -u

PASS=0
FAIL=0

BUILD_DIR="build"
hftac="$BUILD_DIR/hftac"
hftac-naive="$BUILD_DIR/hftac-naive"

pass() {
  echo -e "[\033[32mPASS\033[0m] $1"
  PASS=$((PASS + 1))
}

fail() {
  echo -e "[\033[31mFAIL\033[0m] $1"
  FAIL=$((FAIL + 1))
}

run_check() {
  local name="$1"
  shift

  if "$@"; then
    pass "$name"
  else
    fail "$name"
  fi
}

run_silent() {
  "$@" >/dev/null 2>&1
}

compare_to_tac() {
  local prog="$1"
  local input="$2"
  local student_out="$3"
  local expected_out="$4"
  shift 4

  "$prog" "$@" "$input" > "$student_out" &&
  tac "$input" > "$expected_out" &&
  diff -u "$expected_out" "$student_out" >/dev/null
}


expect_failure() {
  "$@" >/dev/null 2>&1
  [[ $? -ne 0 ]]
}


generate_test_file() {
  local output="$1"
  local size="$2"

  python3 scripts/generate_sentences.py "$output" "$size" >/dev/null 2>&1
}

require_executable() {
  local path="$1"
  [[ -x "$path" ]]
}

cleanup() {
  rm -f grader_small.txt grader_medium.txt grader_large.txt \
        expected_small.out expected_medium.out expected_large.out \
        student_small.out student_medium.out student_large.out \
        student_naive_small.out student_naive_medium.out \
        student_block_3000.out student_block_1024.out
}

trap cleanup EXIT

echo "== Building =="

if ! make clean >/dev/null 2>&1; then
  echo "Warning: make clean failed; continuing"
fi

if make >/dev/null 2>&1; then
  pass "Project builds successfully"
else
  fail "Project builds successfully"
  echo
  echo "Cannot continue because compilation failed."
  echo "Summary: $PASS passed, $FAIL failed"
  exit 1
fi

run_check "hftac executable exists" require_executable "$hftac"
run_check "hftac-naive executable exists" require_executable "$hftac-naive"

if [[ ! -x "$hftac" || ! -x "$hftac-naive" ]]; then
  echo
  echo "Cannot continue because one or more executables are missing."
  echo "Summary: $PASS passed, $FAIL failed"
  exit 1
fi

echo
echo "== Preparing test files =="

run_check "Generated small test file" generate_test_file grader_small.txt 12000
run_check "Generated medium test file" generate_test_file grader_medium.txt 150000
run_check "Generated large test file" generate_test_file grader_large.txt 1500000

if [[ ! -f grader_small.txt || ! -f grader_medium.txt || ! -f grader_large.txt ]]; then
  echo
  echo "Cannot continue because test file generation failed."
  echo "Summary: $PASS passed, $FAIL failed"
  exit 1
fi

echo
echo "== Correctness checks =="

run_check "hftac-naive matches tac on sample.txt" \
  compare_to_tac "$hftac-naive" tests/sample.txt student_naive_small.out expected_small.out

run_check "hftac-naive matches tac on generated medium file" \
  compare_to_tac "$hftac-naive" grader_medium.txt student_naive_medium.out expected_medium.out

run_check "hftac matches tac on sample.txt" \
  compare_to_tac "$hftac" tests/sample.txt student_small.out expected_small.out

run_check "hftac matches tac on one_line.txt" \
  compare_to_tac "$hftac" tests/one_line.txt student_small.out expected_small.out

run_check "hftac matches tac on no_trailing_newline.txt" \
  compare_to_tac "$hftac" tests/no_trailing_newline.txt student_small.out expected_small.out

run_check "hftac matches tac on generated small file" \
  compare_to_tac "$hftac" grader_small.txt student_small.out expected_small.out

run_check "hftac matches tac on generated medium file" \
  compare_to_tac "$hftac" grader_medium.txt student_medium.out expected_medium.out

run_check "hftac with --block-size 3000 matches tac on sample.txt" \
  compare_to_tac "$hftac" tests/sample.txt student_block_3000.out expected_small.out --block-size 3000

run_check "hftac with --block-size 1024 matches tac on generated medium file" \
  compare_to_tac "$hftac" grader_medium.txt student_block_1024.out expected_medium.out --block-size 1024

run_check "hftac rejects block size 0" \
  expect_failure "$hftac" --block-size 0 tests/sample.txt

run_check "hftac rejects missing block size value" \
  expect_failure "$hftac" --block-size
echo
echo "== Timing checks =="

run_check "hftac-naive completes on large file" \
  run_silent "$hftac-naive" grader_large.txt

run_check "hftac completes on large file" \
  run_silent "$hftac" grader_large.txt

run_check "hftac completes on large file with custom block size" \
  run_silent "$hftac" --block-size 8192 grader_large.txt

echo
echo "== Summary =="
echo "$PASS passed, $FAIL failed"

if [[ $FAIL -ne 0 ]]; then
  exit 1
fi