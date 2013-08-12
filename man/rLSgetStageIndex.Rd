\name{rLSgetStageIndex}
\alias{rLSgetStageIndex}

\title{Get the index of a stage by its name.}

\description{
 R interface function for LINDO API function \code{LSgetStageIndex}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetStageIndex(model,pszName)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{pszName}{The name of the stage to return the index for.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnIndex}{Index of the stage.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
