\name{rLSdeleteNLPobj}
\alias{rLSdeleteNLPobj}

\title{Delete NLP elements from the objective function for the given model.}

\description{
 R interface function for LINDO API function \code{LSdeleteNLPobj}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSdeleteNLPobj(model,nCols,paiCols)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nCols}{Number of variables for which NLP elements will be deleted..}
 \item{paiCols}{An integer array containing the indices of the variables whose NLP elements are to be deleted.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
