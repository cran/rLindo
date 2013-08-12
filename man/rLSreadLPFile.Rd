\name{rLSreadLPFile}
\alias{rLSreadLPFile}

\title{Read from file stream in "CPLEX LP Format".}

\description{
 R interface function for LINDO API function \code{LSreadLPFile}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSreadLPFile(model,pszFname)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{pszFname}{The path and name of the LP file.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
