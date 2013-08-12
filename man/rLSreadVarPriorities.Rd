\name{rLSreadVarPriorities}
\alias{rLSreadVarPriorities}

\title{Read branching priorities of variables from a disk file.}

\description{
 R interface function for LINDO API function \code{LSreadVarPriorities}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSreadVarPriorities(model,pszFname)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{pszFname}{The name of the file from which to read the priorities.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSloadVarPriorities}}
}
