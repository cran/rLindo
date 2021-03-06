\name{rLSsolveSP}
\alias{rLSsolveSP}

\title{Solve the SP models.}

\description{
 R interface function for LINDO API function \code{LSsolveSP}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSsolveSP(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnStatus}{An integer reference for the status.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
