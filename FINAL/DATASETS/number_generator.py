def generate_reversed_numbers(n):
    numbers = list(range(n, -1, -1))
    return numbers

def main():
    n = int(input("Enter the number N: "))
    reversed_numbers = generate_reversed_numbers(n)
    filename = input("Enter the filename to save the numbers: ")

    with open(filename, 'w') as file:
        for number in reversed_numbers:
            file.write(str(number) + '\n')

    print(f"{n+1} reversed sorted numbers from {n} to 0 have been generated and saved to {filename}")

if __name__ == "__main__":
    main()
