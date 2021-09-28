


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Do something after an R object is destroyed (i.e. garbage collected)
#'
#' @param obj any R object
#' @param destructor string to print or function to call.  Note: function
#'        must take a single argument which will be an environment
#' @param ... other named values added to environment. E.g. could pass in ID
#'        information so the object which was destroyed could be determined.
#'
#' @return the object with an an added attribute i.e. 'destructor' artefact which
#'         will be called/printed after the object is destroyed (garbage collected)
#'
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
gozer <- function(obj, destructor, ...) {

  if (is.function(destructor)) {
    env <- as.environment(list(...))
    class(env) <- 'gozer_env'
    reg.finalizer(env, destructor)
    attr(obj, 'destructor') <- env
  } else if (is.character(destructor)) {
    ptr <- .Call(gozer_, destructor)
    attr(obj, 'destructor') <- ptr
  } else {
    stop("'destructor' must be a function or string")
  }

  obj
}
