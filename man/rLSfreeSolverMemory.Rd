\name{rLSfreeSolverMemory}
\alias{rLSfreeSolverMemory}

\title{Free up solver work arrays associated with a given model.}

\description{
 R interface function for LINDO API function \code{LSfreeSolverMemory}. For more information,
 please refer to LINDO API User Manual.
}

\details{
  This will release the associated memory to the system, but will cause any subsequent 
  reoptimization of the model to take more time. In other words, the solver will lose 
  its warm start capability for the model on its next run. Note that by freeing solver memory, 
  you will not lose access to the model's solution information.
}

\usage{
  rLSfreeSolverMemory(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
