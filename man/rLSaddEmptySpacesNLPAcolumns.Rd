\name{rLSaddEmptySpacesNLPAcolumns}
\alias{rLSaddEmptySpacesNLPAcolumns}

\title{Add empty space A, this can make inserting constraints more efficient.}

\description{
 R interface function for LINDO API function \code{LSaddEmptySpacesNLPAcolumns}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSaddEmptySpacesNLPAcolumns(model,paiColnnz)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{paiColnnz}{An integer array containing number of spaces to be inserted into each column.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
