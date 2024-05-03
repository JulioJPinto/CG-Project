import sys

def find_unique_lines(file_name):
    unique_lines = {}
    with open(file_name, 'r') as file:
        line_number = 1
        for line in file:
            cleaned_line = line.strip()
            if cleaned_line not in unique_lines:
                unique_lines[cleaned_line] = line_number
            line_number += 1
    
    return unique_lines

def main():
    if len(sys.argv) != 2:
        print("Usage: python program_name.py <file_path>")
        return
    
    file_name = sys.argv[1]
    unique_lines = find_unique_lines(file_name)
    print(f"Number of Unique lines: {unique_lines.__len__() - 1}")
    
if __name__ == "__main__":
    main()
