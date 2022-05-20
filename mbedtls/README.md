
## Get source code

```
git clone https://github.com/Mbed-TLS/mbedtls.git -b v2.28.0
```

## Config and compile

### Set output dir

```diff
diff --git a/Makefile b/Makefile
index 5b2ad16cd..5c9a63ed4 100644
--- a/Makefile
+++ b/Makefile
@@ -1,4 +1,4 @@
-DESTDIR=/usr/local
+DESTDIR=./output
 PREFIX=mbedtls_
 PERL ?= perl
```

### Exclude the X.509 and TLS

```
scripts/config.py crypto
```

Refer to [here](https://github.com/ARMmbed/mbed-crypto/blob/8cc246c6d33a139914d3070c6cf630aea6806aa4/README.md).

### Build

```
make
```

### Install

```
make install
```
