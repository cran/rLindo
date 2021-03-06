\name{rLSgetDInfo}
\alias{rLSgetDInfo}

\title{Return model or solution double information about the current state of 
       the LINDO API solver after model optimization is completed.}

\description{
 R interface function for LINDO API function \code{LSgetDInfo}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetDInfo(model,nQuery)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nQuery}{Number of stages/blocks in the dual angular model.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pdResult}{A double value for requested information.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSgetIInfo}}
}

