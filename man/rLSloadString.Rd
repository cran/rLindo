\name{rLSloadString}
\alias{rLSloadString}

\title{Load a single string into a model structure.}

\description{
 R interface function for LINDO API function \code{LSloadString}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSloadString(model,pszString)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{pszString}{A null terminated string.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
