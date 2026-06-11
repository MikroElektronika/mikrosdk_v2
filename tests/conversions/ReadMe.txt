Bare-metal test for conversions.h/.c. Results reported over logger.

Each test group prints a header and FAIL lines for any mismatch.
Final line shows total pass/fail counts.

Covers: hex, decimal string, zero-padded string, BCD, trim, float_to_str,
float_to_str_prec, str-to-numeric (all widths), and hex-to-int conversions.
