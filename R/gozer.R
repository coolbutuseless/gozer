

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Do something after an R object is destroyed (i.e. garbage collected)
#'
#' @param obj any R object
#' @param destructor string to print or function to call.  Note: function
#'        takes a single argument which should be discarded
#'
#' @return the object with an an added attribute.  A 'destructor' artefact which
#'         will be printed/called after the object is destroyed.
#'
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
gozer <- function(obj, destructor) {
  ptr <- .Call(gozer_, destructor)
  attr(obj, 'destructor') <- ptr
  obj
}
