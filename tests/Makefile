REPO_ROOT := ../

SRCS := test_compile/GameHooks.cpp \
        $(REPO_ROOT)src/main.cpp \
        $(REPO_ROOT)src/SSLanguageController.cpp \
        $(REPO_ROOT)src/SSLocal.cpp \
        $(REPO_ROOT)src/SSLocalDatabase.cpp

INCLUDES := -I$(REPO_ROOT)include \
            -I$(REPO_ROOT)shared \
            -I$(REPO_ROOT)tests/test_include \
            -I$(REPO_ROOT)extern/includes/fmt/fmt/include

LIBS := -lfmt

CXX := clang++
CXXFLAGS := -g

test1.run: mains/test1.cpp $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $< $(SRCS) $(INCLUDES) $(LIBS)

csv_loader.run: mains/csv_loader.cpp $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $< $(SRCS) $(INCLUDES) $(LIBS)

.PHONY: clean
clean:
	rm -f test1.run
