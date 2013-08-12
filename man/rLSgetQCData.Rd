\name{rLSgetQCData}
\alias{rLSgetQCData}

\title{Retrieve the quadratic data from a model data structure.}

\description{
 R interface function for LINDO API function \code{LSgetQCData}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetQCData(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{paiQCrows}{An integer array containing the index of the constraint associated 
                  with each quadratic term with a nonzero coefficient.}
 \item{paiQCcols1}{An integer array containing the index of the first variable 
                   defining each quadratic term.}
 \item{paiQCcols2}{An integer array containing the index of the second variable 
                   defining each quadratic term.}
 \item{padQCcoef}{A double array containing the nonzero coefficients in the quadratic matrix.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSloadQCData}}
}