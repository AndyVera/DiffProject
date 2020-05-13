#include "DiffFunctions.h"

int main(int argc, const char * argv[]) {
    if(argc <= 1){
        printErrorInput();
        exit(1);
    }
    
    if(argc == 2 && strcmp(argv[1], "--help") == 0){printOptions();}
    if(argc == 2 && strcmp(argv[1], "-v") == 0 ){ printVersion(); }
    if(argc == 4 && strcmp(argv[1], "-q") == 0){ printDifferent(argv[2], argv[3]); }
    if(argc == 4 && strcmp(argv[1], "-s") == 0){ printSame(argv[2], argv[3]); }
    if(argc == 5 && strcmp(argv[1], "-s") == 0 && strcmp(argv[2], "-q") == 0){ printSameOrDifferent(argv[3], argv[4]); }
    if(argc == 3){ printDefaultMode(argv[1], argv[2]); }
    if(argc == 4 && strcmp(argv[1], "-y") == 0){printSidebySide(argv[2], argv[3]); }
    if(argc == 5 && strcmp(argv[1], "-y") == 0 && strcmp(argv[2], "--left-column") == 0){ printLeftColumn(argv[3], argv[4]); }
    if(argc == 5 && strcmp(argv[1], "-y") == 0 && strcmp(argv[2], "--suppress-common-lines") == 0){ printNonSuppressedLines(argv[3], argv[4]); }
}
