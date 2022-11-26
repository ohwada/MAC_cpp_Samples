binary: base64
===============

convert binary to/from base64 encoding

## samples
- test_base64.c
- test_image_file.c


Build and Run:  
% make test  
% bin/test  
> BASE64("") = ""
> DATA("") = ""
> BASE64("f") = "Zg=="
> DATA("Zg==") = "f"
> successful
