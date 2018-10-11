"""Simple utility to concatenate the files in this program into a single file.
   This is due to the fact that the professor has hundreds of students and 
   doesn't want to fiddle with lots and lots of files."""


TARGET_NAME = "consolidated_rref.cpp"


def write_comment(fh, s):
    fh.write("\n// {}\n\n".format(s))


def write_file(fh, filename):
    with open(filename) as source:
        for line in source:
            fh.write(line)


FILES = ["row.h",
         "matrix.h",
         "row.cpp",
         "matrix.cpp",
         "rref.cpp"]

COMMENTS = ["Header file for Row class",
            "Header file for Matrix class",
            "Implementation file for Row class",
            "Implementation file for Matrix class",
            "Main program"]

if __name__ == "__main__":
    with open(TARGET_NAME, 'w') as f:
        write_comment(f, "Consolidated rref program. See " +
                         "github.com/mbottini/rref for separate files.")
        for filename, comment in zip(FILES, COMMENTS):
            print("Writing comment: {}...".format(comment))
            write_comment(f, comment)

            print("Writing file: {}...".format(filename))
            write_file(f, filename)
