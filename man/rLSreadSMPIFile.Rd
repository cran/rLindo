\name{rLSreadSMPIFile}
\alias{rLSreadSMPIFile}

\title{Read the CORE,TIME,STOCH files for SP models in SMPI format.}

\description{
 R interface function for LINDO API function \code{LSreadSMPIFile}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSreadSMPIFile(model,pszCorefile,pszTimefile,pszStocfile)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{pszCorefile}{Path and name of the CORE file in MPS format.}
 \item{pszTimefile}{Path and name of the TIME file.}
 \item{pszStocfile}{Path and name of the STOCH file.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
