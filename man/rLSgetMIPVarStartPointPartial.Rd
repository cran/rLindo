\name{rLSgetMIPVarStartPointPartial}
\alias{rLSgetMIPVarStartPointPartial}

\title{Retrieve the resident initial point for MIP/MINLP models.}

\description{
 R interface function for LINDO API function \code{LSgetMIPVarStartPointPartial}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetMIPVarStartPointPartial(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnCols}{The number of variables in the partial solution.}
 \item{paiCols}{An integer array containing the indicies of variables in the partial solution.}
 \item{panPrimal}{An integer array containing the values of the partial solution.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSloadMIPVarStartPointPartial}}
}