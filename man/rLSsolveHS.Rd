\name{rLSsolveHS}
\alias{rLSsolveHS}

\title{Solve the given model heuristically using the specified search method.}

\description{
 R interface function for LINDO API function \code{LSsolveHS}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSsolveHS(model,nSearchMethod)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nSearchMethod}{An integer macro specifying the heuristic search method.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnStatus}{An integer reference for the status.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
