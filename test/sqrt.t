def sqrt(n) {
    e = 1;
    while (|((t = n/e) - e) > 0.001) {
        e = avg(e, t);
    }
}

def avg(a, b) {
    (a + b) / 2;
}

sqrt(10);
