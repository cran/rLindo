\name{rLSgetBestBounds}
\alias{rLSgetBestBounds}

\title{Finds the best implied variable bounds for the specified model by 
       improving the original bounds using extensive preprocessing and probing.}

\description{
 R interface function for LINDO API function \code{LSgetBestBounds}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSgetBestBounds(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{padBestL}{Best implied lower bounds if different from NULL.}
 \item{padBestU}{Best implied upper bounds if different from NULL.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
