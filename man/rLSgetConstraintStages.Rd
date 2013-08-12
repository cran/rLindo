\name{rLSgetConstraintStages}
\alias{rLSgetConstraintStages}

\title{Retrieve the stage indices of constraints.}

\description{
 R interface function for LINDO API function \code{LSgetConstraintStages}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetConstraintStages(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{panStage}{An integer array containing the stage indices of constraints in the core model.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
