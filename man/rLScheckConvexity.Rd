\name{rLScheckConvexity}
\alias{rLScheckConvexity}

\title{Optimize a quadratic model with the best suitable solver.}

\description{
 R interface function for LINDO API function \code{LScheckConvexity}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLScheckConvexity(model)
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

