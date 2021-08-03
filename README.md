Utility for Windows to read text files with CRLF and strip the CR character.
I know there are a bunch out there, but they didn't seem to work. 

For example, **tr** created 2 byte output for each character, and include a BOM.

There are utils for unix, but this had to be run on Windows.

    C:> dos2unix.exe
    dos2unix by Lee Patterson http://axorion.com
    Strips CR (0x0D) from text files.
    Usage: dos2unix [-v] source destination
    -v = verbose

    C:> dos2unix.exe -v .\a.txt .\b.txt
    in : 6C (108) l
    out: 6C (108) l
    in : 73 (115) s
    out: 73 (115) s
    in : 20 (32)
    out: 20 (32)
    in : 2D (45) -
    out: 2D (45) -
    in : 61 (97) a
    out: 61 (97) a
    in : 0D (13) .<stripped>
    in : 0A (10) .
    out: 0A (10) .
    in : 6C (108) l
    out: 6C (108) l
    in : 73 (115) s
    out: 73 (115) s
    in : 20 (32)
    out: 20 (32)
    in : 2D (45) -
    out: 2D (45) -
    in : 6C (108) l
    out: 6C (108) l
    in : 0D (13) .<stripped>
    in : 0A (10) .
    out: 0A (10) .