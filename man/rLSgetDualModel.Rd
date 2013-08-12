\name{rLSgetDualModel}
\alias{rLSgetDualModel}

\title{Construct the explicit dual from a primal problem.}

\description{
 R interface function for LINDO API function \code{LSgetDualModel}. For more information,
 please refer to LINDO API User Manual.
}

\details{
 The dual has its own memory blocks and does not share any with the primal.
}

\usage{
  rLSgetDualModel(model,dualmodel)
}

\arguments{
 \item{model}{Primal model. A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{dualmodel}{Dual model. A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

