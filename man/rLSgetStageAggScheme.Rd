\name{rLSgetStageAggScheme}
\alias{rLSgetStageAggScheme}

\title{Get stage aggregation scheme for the SP model.}

\description{
 R interface function for LINDO API function \code{LSgetStageAggScheme}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetStageAggScheme(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{panScheme}{An integer array containing the stage aggregation scheme.}
 \item{pnLength}{Length of panScheme.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
