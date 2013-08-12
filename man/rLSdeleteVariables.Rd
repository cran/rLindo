\name{rLSdeleteVariables}
\alias{rLSdeleteVariables}

\title{Delete a set of variables in the given model.}

\description{
 R interface function for LINDO API function \code{LSdeleteVariables}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSdeleteVariables(model,nVars,paiVars)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nVars}{Number of variables to be deleted.}
 \item{paiVars}{An integer array containing the indices of the ariables to be deleted.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

