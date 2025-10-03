# General
Please follow the instructions shared in advance to install the tutorial BEFORE YOU ARRIVE to the tutorial. We strongly suggest you do this a few days before the conference, so you have some time to deal with installation issues, if you encounter any. 
We will not spend time in the tutorial on installations, and arriving with a PC that is not ready would mean you will spend much of the tutorial time on mundane installations. 
If you encounter problems installing, try first Google, ChatGPT, Microsoft CoPilot or your favourite knowledge source. If all else fails, contact the tutorial owner Luis Dias  at l.dias@andersenlab.com

1) Clean up old build artifacts and coverage files

cd ~/MyProjectGTest

# remove all build directories (adjust if you have others)
rm -rf build GTest/build external/googletest/build

# remove any stray coverage files in the repo
find . -name '*.gcda' -o -name '*.gcno' -delete


2) Reconfigure and rebuild everything with GCC/G++ 11.4

CC=/usr/bin/gcc-11 CXX=/usr/bin/g++-11 \
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j
./build/run_tests


3) Generate the HTML branch coverage report

gcovr -r . build \
  --exclude 'test/.*' \
  --filter 'src/.*' \
  --html --html-details --branches \
  --gcov-executable /usr/bin/gcov-11 \
  -o coverage_report.html