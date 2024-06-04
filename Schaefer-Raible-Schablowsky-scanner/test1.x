PROG fibonacci.

VAR
    ?int n.
    int count.
    int minus1.
    int minus2.
    !int current.
END_VAR

EXEC
    minus1 = 0.
    minus2 = 1.
        
    /* conut is wrong */
    for conut = 0 . count < (n - 2) . count += 1 do
        current = minus1 + minus2.
        minus1 = minus2.
        /* currnet is wrong */
        minus2 = currnet.
    endfor
END_EXEC
