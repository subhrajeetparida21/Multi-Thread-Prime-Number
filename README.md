# OS Assignment 1

This folder contains our submission for the OS Assignment 1 (Parallel Prime Generator).

There are two folders:

1. **FASTprime MAN**: 
   - This checks my manual implementation.
   - Run `prime.c` to see it working.
   - Plots are in the `results` folder.

2. **FASTprime AI**:
   - This has the AI generated code (`primeAI.c`).
   - I used Gemini for this.
   - Prompt info is in `ai_meta.txt`.

## How to Execute

### 1. Manual Code
Go to the manual folder:
```bash
cd "FASTprime MAN"
gcc prime.c -lm
./a.out
```

### 2. AI Code
Go to the AI folder:
```bash
cd "../FASTprime AI" 

gcc primeAI.c -lm
./a.out
```

