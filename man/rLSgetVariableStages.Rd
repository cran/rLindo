\name{rLSgetVariableStages}
\alias{rLSgetVariableStages}

\title{Retrieve the stage indices of variables.}

\description{
 R interface function for LINDO API function \code{LSgetVariableStages}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetVariableStages(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{panStage}{An integer array containing the stage indices of variables in the core model.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
