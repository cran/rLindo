\name{rLSgetProbabilityByNode}
\alias{rLSgetProbabilityByNode}

\title{Return the probability of a given node in the stochastic tree.}

\description{
 R interface function for LINDO API function \code{LSgetProbabilityByNode}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetProbabilityByNode(model,iNode)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iNode}{An integer specifying the node index.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pdProb}{The probabability of the node.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
