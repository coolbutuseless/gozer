
<!-- README.md is generated from README.Rmd. Please edit that file -->

# gozer - choose the form of the destructor <img src="man/figures/logo.png" align="right" height="230/"/>

<!-- badges: start -->

![](https://img.shields.io/badge/cool-useless-green.svg)
<!-- badges: end -->

`gozer` allows you to attach a ‘destructor’ artefact (a function to call
or string to print) to an R object.

After the R object is destroyed (i.e. garbage collected) the
‘destructor’ artefact is called/printed.

## What’s in the box

-   `gozer()` to attach a destructor artefact to an object.

## Installation

You can install from [GitHub](https://github.com/coolbutuseless/gozer)
with:

``` r
# install.package('remotes')
remotes::install_github('coolbutuseless/gozer')
```

## Printing a string as a ‘destructor’ artefact.

``` r
library(gozer)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Define an object and add a string as a destruction artefact
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
a <- 'hello'
a <- gozer(a, 'This object has now said goodbye')
a
```

    #> [1] "hello"
    #> attr(,"destructor")
    #> <pointer: 0x0>
    #> attr(,"class")
    #> [1] "gozer_string"

``` r
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Destroy the object and get the destruction artefact
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
rm(a)

invisible(gc())
```

    #> This object has now said goodbye

## Calling a function as a ‘destructor’ artefact.

``` r
library(gozer)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Function to call when object is destroyed. 
# Argument will be an external pointer object which is unusable
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ff <- function(env) {
  cat("There was definitely a garbage collection event for object:", env$id, "\n")
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Define an object and add a function as a destruction artefact
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
a <- 'hello'
a <- gozer(a, ff, id = 'test 1')
a
```

    #> [1] "hello"
    #> attr(,"destructor")
    #> <environment: 0x7f92321ebb20>
    #> attr(,"class")
    #> [1] "gozer_env"

``` r
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Destroy the object and get the destruction artefact
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
rm(a)

invisible(gc())
```

    #> There was definitely a garbage collection event for object: test 1

## Related Software

-   `base::reg.finalizer()`
    -   Only works on environments and external pointers
    -   Object is still active at the time of finalization and is the
        expected argument to the finalizer function.
-   R6 ‘finalize’ method

## Acknowledgements

-   R Core for developing and maintaining the language.
-   CRAN maintainers, for patiently shepherding packages onto CRAN and
    maintaining the repository

## Gozer the Gozerian

<img src="man/figures/gozer.jpg">
