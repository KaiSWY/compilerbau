PROG fibonacci

VAR
    int? n
    int count
    @int minus1
    int minus2
    int! current
END_VAR

EXEC
    /* missing . and illegal char @ */
    minus1 = 0.
    minus2 = 1.
    
    for count = 0 . count < (n - 2) . count += 1 do
        current = minus1 + minus2.
        minus1 = minus2.
        minus2 = current.
    endfor
END_EXEC
