import random
import argparse

def generate_skyscraper_grid(size):
    """Generates a valid Latin Square of a given size."""
    grid = [[0] * size for _ in range(size)]
    
    def is_valid(r, c, val):
        for i in range(size):
            if grid[r][i] == val or grid[i][c] == val:
                return False
        return True

    def solve():
        for r in range(size):
            for c in range(size):
                if grid[r][c] == 0:
                    numbers = list(range(1, size + 1))
                    random.shuffle(numbers)
                    for val in numbers:
                        if is_valid(r, c, val):
                            grid[r][c] = val
                            if solve():
                                return True
                            grid[r][c] = 0
                    return False
        return True

    solve()
    return grid

def count_visible(line):
    """Calculates how many buildings are visible from one end of a line."""
    visible_count = 0
    max_height = 0
    for height in line:
        if height > max_height:
            visible_count += 1
            max_height = height
    return visible_count

def get_clues(grid, size):
    """Generates the clues for top, bottom, left, and right."""
    clues = {
        "top": [count_visible([grid[r][c] for r in range(size)]) for c in range(size)],
        "bottom": [count_visible([grid[r][c] for r in range(size-1, -1, -1)]) for c in range(size)],
        "left": [count_visible(grid[r]) for r in range(size)],
        "right": [count_visible(grid[r][::-1]) for r in range(size)]
    }
    return clues

def display_puzzle(grid, clues, size):
    """Prints the puzzle in a readable format."""
    print(f"    {' '.join(map(str, clues['top']))}")
    print(f"    {'-' * (size * 2 - 1)}")
    for i in range(size):
        print(f"{clues['left'][i]} | {' '.join(map(str, grid[i]))} | {clues['right'][i]}")
    print(f"    {'-' * (size * 2 - 1)}")
    print(f"    {' '.join(map(str, clues['bottom']))}")

def display_clues_in_file(clues, outfile:str):
    top = clues["top"]
    bottom = clues["bottom"]
    left = clues["left"]
    right = clues["right"]
    with open(outfile, "a") as f:
        for number in top:
            f.write(str(number) + " ")
        for number in bottom:
            f.write(str(number) + " ")
        for number in left:
            f.write(str(number) + " ")
        for number in right:
            f.write(str(number) + " ")
        f.write("\n")

def main():
    parser = argparse.ArgumentParser(description="Generate Skyscraper Puzzles")
    parser.add_argument("-c", "--count", type=int, help="Number of grids to generate", default=1)
    parser.add_argument("-s", "--size", type=int, help="Size of the grid (e.g., 4 for a 4x4)", default=8)
    parser.add_argument("-o", "--outfile", type=int, help="Size of the grid (e.g., 4 for a 4x4)", default=8)
    
    args = parser.parse_args()
    
    generated_grids = set()
    attempts = 0
    
    while len(generated_grids) < args.count and attempts < args.count * 10:
        grid = generate_skyscraper_grid(args.size)
        grid_tuple = tuple(tuple(row) for row in grid)
        
        if grid_tuple not in generated_grids:
            generated_grids.add(grid_tuple)
            clues = get_clues(grid, args.size)
            display_clues_in_file(clues, f"{args.size}x{args.size}.txt")
        
        attempts += 1

if __name__ == "__main__":
    main()