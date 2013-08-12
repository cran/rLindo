\name{rLSgetStocSInfo}
\alias{rLSgetStocSInfo}

\title{Get string information about the current state of the stochastic model.}

\description{
 R interface function for LINDO API function \code{LSgetStocInfo}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetStocSInfo(model,nQuery,nParam)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nQuery}{A valid information macro.}
 \item{nParam}{The parameter of the query.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pszResult}{A string value of the information.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
