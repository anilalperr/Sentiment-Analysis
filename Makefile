CC := clang
CFLAGS := -g -Wall -Werror

all: sentiment_analysis

clean:
	@echo "Removing build output"
	@rm -rf sentiment_analysis.dSYM sentiment_analysis sentiment_analysis.zip

sentiment_analysis: sentiment_analysis.c
	$(CC) $(CFLAGS) -o sentiment_analysis sentiment_analysis.c

zip:
	@echo "Generating sentiment_analysis.zip file to submit to Gradescope..."
	@zip -q -r sentiment_analysis.zip . -x .git/\* .vscode/\* .clang-format .gitignore sentiment_analysis
	@echo "Done. Please upload sentiment_analysis.zip to Gradescope."

format:
	@echo "Reformatting source code."
	@clang-format -i --style=file $(wildcard *.c) $(wildcard *.h)
	@echo "Done."

.PHONY: all clean zip format
