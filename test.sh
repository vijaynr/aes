#!/bin/bash

# Simple test script for Simplified AES implementation
# Tests various input values and verifies round-trip encryption/decryption

echo "=== Simplified AES Test Suite ==="
echo

# Test cases - various 16-bit values
test_cases=("0000" "1234" "ABCD" "FFFF" "5555" "AAAA" "1111" "8888")

build_program() {
    echo "Building AES program..."
    make clean > /dev/null 2>&1
    if ! make > /dev/null 2>&1; then
        echo "❌ Build failed!"
        exit 1
    fi
    echo "✅ Build successful"
    echo
}

run_test() {
    local input=$1
    echo "Testing input: $input"
    
    # Run the program and capture output
    result=$(echo "$input" | ./aes 2>/dev/null)
    
    # Extract the success/failure indicator
    if echo "$result" | grep -q "✓ Encryption/Decryption successful"; then
        echo "✅ Test passed for $input"
        # Extract cipher text for information
        cipher=$(echo "$result" | grep "Encoded Cipher Text" | awk '{print $NF}')
        echo "   $input → $cipher → $input"
    else
        echo "❌ Test failed for $input"
        return 1
    fi
    echo
}

# Main test execution
build_program

failed_tests=0
total_tests=${#test_cases[@]}

echo "Running tests on $total_tests test cases..."
echo

for test_case in "${test_cases[@]}"; do
    if ! run_test "$test_case"; then
        ((failed_tests++))
    fi
done

echo "=== Test Results ==="
echo "Total tests: $total_tests"
echo "Passed: $((total_tests - failed_tests))"
echo "Failed: $failed_tests"

if [ $failed_tests -eq 0 ]; then
    echo "🎉 All tests passed!"
    exit 0
else
    echo "💥 Some tests failed!"
    exit 1
fi