\name{rLSmodifyUpperBounds}
\alias{rLSmodifyUpperBounds}

\title{Modify selected upper bounds in a given model.}

\description{
 R interface function for LINDO API function \code{LSmodifyUpperBounds}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSmodifyUpperBounds(model,nVars,paiVars,padU)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nVars}{Number of bounds in the model to modify.}
 \item{paiVars}{An integer array containing the indices of the variables for which to modify the upper bounds.}
 \item{padU}{A double array containing the new values of the upper bounds on the variables.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

