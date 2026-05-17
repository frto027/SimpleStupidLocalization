REPO_ROOT=../
COMPILE_ARGS="test_compile/GameHooks.cpp\
 ${REPO_ROOT}src/main.cpp\
 ${REPO_ROOT}src/SSLanguageController.cpp \
 ${REPO_ROOT}src/SSLocal.cpp \
 ${REPO_ROOT}src/SSLocalDatabase.cpp \
 -I${REPO_ROOT}include \
 -I${REPO_ROOT}shared \
 -I${REPO_ROOT}/tests/test_include \
 -I${REPO_ROOT}/extern/includes/fmt/fmt/include \
 -lfmt"

clang++ -g -o test1.run mains/test1.cpp $COMPILE_ARGS