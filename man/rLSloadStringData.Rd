\name{rLSloadStringData}
\alias{rLSloadStringData}

\title{Load a vector of strings into a model structure and get sort order.}

\description{
 R interface function for LINDO API function \code{LSloadStringData}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSloadStringData(model,nStrings,paszStringData)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nStrings}{Number of strings to load.}
 \item{paszStringData}{A string array containing the strings.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
