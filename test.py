import os


def main():
    from tld_module import sayHello
    
    sayHello()


if __name__ == "__main__":
    os.add_dll_directory("C:/msys64/mingw64/bin")
    main()
