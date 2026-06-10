# PGM-Image-median-filter
A high-performance C++ command-line application designed to eliminate noise from grayscale images using a Median Filter. The application parses, processes, and writes images natively using the ASCII PGM (Portable GrayMap) P2 file format.

FEATURES:

    1) Supports any odd-sized filtering matrix (3x3, 5x5, 7x7 etc.)
    2) Allows switching between Bubble Sort and Merge Sort based on user input
    3) Supports Full HD resolution (1920x1080) with proper memory cleanup
    4) Replicates edge pixels without allocating extra memory via oversized matrices

HOW IT WORKS:

    1) Format Parsing: Reads the PGM metadata (Magic value P2, Width, Height, and Max   Gray Value) while bypassing comments (#)
    2) Window identification: For every pixel, a local spatial "neighborhood" matrix (W x W) is evaluated. For the edge-bound 
    pixels, each of their values are copied in the sorting-bound vector, thus reducing memory usage significantly by 
    not having to physically extend the matrix.
    3) Median Computation: The collected neighborhood values are loaded into a vector, sorted via the user's 
    selected algorithm (bubble or merge), and the center (median) element replaces the original pixel value.

INPUT FORMAT: 

    The application expects parameters via the standard input stream (cin) on a single line, separated by 
    whitespace: "<user_algorithm> <window_size> <input_file_path> <output_file_path>". 
    "<user_algorithm>" may be either "bubble" or "merge", "<window_size> must be an odd, positive integer 
    representing the filtering window size, the input file represents the noisy source .pgm image and 
    the output file is the clean, reconstructed image.

BUILDING AND RUNNING:

    1) Prerequisites: A C++ compiler supporting standard C++11 or newer (e.g., g++ via MSYS2/MinGW, Clang, or MSVC).
    2) Compilation: Compile the source file using your terminal via a typical compiling command e.g. "g++ main.cpp -o median_filter"
    3) Running the app: execute the compiled file (e.g. "./median_filter") and type or paste your input parameters directly
    into the terminal window (e.g. "bubble 3 input_noise.pgm output_filtered.pgm")

FORMAT SPECIFICATIONS: This application supports only the Netbpm P2 (text) layout. 
