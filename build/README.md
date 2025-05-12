# Set name and email in GIT
git config --global user.name "Luisdias" 
git config --global user.email "l.dias@andersenlab.com" 


# Compile, build and run tests 
cmake .. 
make 
./run_tests


# Coverage generation 
lcov --directory . --capture --output-file coverage.info
lcov --remove coverage.info '/usr/*' '*/external/*' --output-file filtered_coverage.info
genhtml filtered_coverage.info --output-directory coverage_html