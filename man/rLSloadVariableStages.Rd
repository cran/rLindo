\name{rLSloadVariableStages}
\alias{rLSloadVariableStages}

\title{Load stage structure of the variables in the model.}

\description{
 R interface function for LINDO API function \code{LSloadVariableStages}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSloadVariableStages(model,panStage)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{panStage}{An integer array containing information about the stage membership of the variables.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
