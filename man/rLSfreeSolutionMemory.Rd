\name{rLSfreeSolutionMemory}
\alias{rLSfreeSolutionMemory}

\title{Free up the arrays associated with the solution of a given model.}

\description{
 R interface function for LINDO API function \code{LSfreeSolutionMemory}. For more information,
 please refer to LINDO API User Manual.
}

\details{
  This will release the associated memory blocks to the system, but will not cause the solver 
  to loose any warm start capability for the model on its next run. However, you will lose 
  all access to the model's solution information.
}

\usage{
  rLSfreeSolutionMemory(model)
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
