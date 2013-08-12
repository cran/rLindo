\name{rLSdeleteString}
\alias{rLSdeleteString}

\title{Delete the complete string data, including the string vector and values.}

\description{
 R interface function for LINDO API function \code{LSdeleteString}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSdeleteString(model)
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
